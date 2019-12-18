#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int example_hashes; int keyspace; int left; int backend_info; int show; int usage; int version; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_13__ {scalar_t__ attack_kern; } ;
typedef  TYPE_2__ user_options_extra_t ;
struct TYPE_14__ {int enabled; size_t alias_cnt; size_t entry_cnt; TYPE_4__* entry_buf; TYPE_4__* alias_buf; } ;
typedef  TYPE_3__ tuning_db_t ;
struct TYPE_15__ {int attack_mode; int hash_mode; int vector_width; int kernel_accel; int kernel_loops; void* device_name; void* alias_name; } ;
typedef  TYPE_4__ tuning_db_entry_t ;
typedef  TYPE_4__ tuning_db_alias_t ;
struct TYPE_16__ {TYPE_2__* user_options_extra; TYPE_1__* user_options; TYPE_3__* tuning_db; TYPE_7__* folder_config; } ;
typedef  TYPE_6__ hashcat_ctx_t ;
struct TYPE_17__ {int /*<<< orphan*/  shared_dir; } ;
typedef  TYPE_7__ folder_config_t ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 scalar_t__ ATTACK_KERN_BF ; 
 scalar_t__ ATTACK_KERN_COMBI ; 
 scalar_t__ ATTACK_KERN_STRAIGHT ; 
 scalar_t__ HCBUFSIZ_LARGE ; 
 int KERNEL_BFS ; 
 int KERNEL_COMBS ; 
 int KERNEL_RULES ; 
 int /*<<< orphan*/  TUNING_DB_FILE ; 
 size_t count_lines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_6__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_log_warning (TYPE_6__*,char*,int,...) ; 
 int /*<<< orphan*/  hc_asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_feof (int /*<<< orphan*/ *) ; 
 char* hc_fgets (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  hc_rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ hccalloc (size_t const,int) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (scalar_t__) ; 
 void* hcstrdup (char*) ; 
 size_t in_superchop (char*) ; 
 int /*<<< orphan*/  qsort (TYPE_4__*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_by_tuning_db_alias ; 
 int /*<<< orphan*/  sort_by_tuning_db_entry ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* strtok_r (char*,char*,char**) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 

int tuning_db_init (hashcat_ctx_t *hashcat_ctx)
{
  folder_config_t       *folder_config      = hashcat_ctx->folder_config;
  tuning_db_t           *tuning_db          = hashcat_ctx->tuning_db;
  user_options_t        *user_options       = hashcat_ctx->user_options;
  user_options_extra_t  *user_options_extra = hashcat_ctx->user_options_extra;

  tuning_db->enabled = false;

  if (user_options->example_hashes == true) return 0;
  if (user_options->keyspace       == true) return 0;
  if (user_options->left           == true) return 0;
  if (user_options->backend_info   == true) return 0;
  if (user_options->show           == true) return 0;
  if (user_options->usage          == true) return 0;
  if (user_options->version        == true) return 0;

  tuning_db->enabled = true;

  char *tuning_db_file;

  hc_asprintf (&tuning_db_file, "%s/%s", folder_config->shared_dir, TUNING_DB_FILE);

  HCFILE fp;

  if (hc_fopen (&fp, tuning_db_file, "rb") == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", tuning_db_file, strerror (errno));

    return -1;
  }

  hcfree (tuning_db_file);

  const size_t num_lines = count_lines (&fp);

  // a bit over-allocated

  tuning_db->alias_buf = (tuning_db_alias_t *) hccalloc (num_lines + 1, sizeof (tuning_db_alias_t));
  tuning_db->alias_cnt = 0;

  tuning_db->entry_buf = (tuning_db_entry_t *) hccalloc (num_lines + 1, sizeof (tuning_db_entry_t));
  tuning_db->entry_cnt = 0;

  hc_rewind (&fp);

  int line_num = 0;

  char *buf = (char *) hcmalloc (HCBUFSIZ_LARGE);

  while (!hc_feof (&fp))
  {
    char *line_buf = hc_fgets (buf, HCBUFSIZ_LARGE - 1, &fp);

    if (line_buf == NULL) break;

    line_num++;

    const size_t line_len = in_superchop (line_buf);

    if (line_len == 0) continue;

    if (line_buf[0] == '#') continue;

    // start processing

    char *token_ptr[7] = { NULL };

    int token_cnt = 0;

    char *saveptr = NULL;

    char *next = strtok_r (line_buf, "\t ", &saveptr);

    token_ptr[token_cnt] = next;

    token_cnt++;

    while ((next = strtok_r ((char *) NULL, "\t ", &saveptr)) != NULL)
    {
      token_ptr[token_cnt] = next;

      token_cnt++;
    }

    if (token_cnt == 2)
    {
      char *device_name = token_ptr[0];
      char *alias_name  = token_ptr[1];

      tuning_db_alias_t *alias = &tuning_db->alias_buf[tuning_db->alias_cnt];

      alias->device_name = hcstrdup (device_name);
      alias->alias_name  = hcstrdup (alias_name);

      tuning_db->alias_cnt++;
    }
    else if (token_cnt == 6)
    {
      if ((token_ptr[1][0] != '0') &&
          (token_ptr[1][0] != '1') &&
          (token_ptr[1][0] != '3') &&
          (token_ptr[1][0] != '*'))
      {
        event_log_warning (hashcat_ctx, "Tuning-db: Invalid attack_mode '%c' in Line '%d'", token_ptr[1][0], line_num);

        continue;
      }

      if ((token_ptr[3][0] != '1') &&
          (token_ptr[3][0] != '2') &&
          (token_ptr[3][0] != '4') &&
          (token_ptr[3][0] != '8') &&
          (token_ptr[3][0] != 'N'))
      {
        event_log_warning (hashcat_ctx, "Tuning-db: Invalid vector_width '%c' in Line '%d'", token_ptr[3][0], line_num);

        continue;
      }

      char *device_name = token_ptr[0];

      int attack_mode      = -1;
      int hash_mode        = -1;
      int vector_width     = -1;
      int kernel_accel     = -1;
      int kernel_loops     = -1;

      if (token_ptr[1][0] != '*') attack_mode   = (int) strtol (token_ptr[1], NULL, 10);
      if (token_ptr[2][0] != '*') hash_mode     = (int) strtol (token_ptr[2], NULL, 10);
      if (token_ptr[3][0] != 'N') vector_width  = (int) strtol (token_ptr[3], NULL, 10);

      if (token_ptr[4][0] == 'A')
      {
        kernel_accel = 0;
      }
      else if (token_ptr[4][0] == 'M')
      {
        kernel_accel = 1024;
      }
      else
      {
        kernel_accel = (int) strtol (token_ptr[4], NULL, 10);

        if ((kernel_accel < 1) || (kernel_accel > 1024))
        {
          event_log_warning (hashcat_ctx, "Tuning-db: Invalid kernel_accel '%d' in Line '%d'", kernel_accel, line_num);

          continue;
        }
      }

      if (token_ptr[5][0] == 'A')
      {
        kernel_loops = 0;
      }
      else if (token_ptr[5][0] == 'M')
      {
        if (user_options_extra->attack_kern == ATTACK_KERN_STRAIGHT)
        {
          kernel_loops = KERNEL_RULES;
        }
        else if (user_options_extra->attack_kern == ATTACK_KERN_COMBI)
        {
          kernel_loops = KERNEL_COMBS;
        }
        else if (user_options_extra->attack_kern == ATTACK_KERN_BF)
        {
          kernel_loops = KERNEL_BFS;
        }
      }
      else
      {
        kernel_loops = (int) strtol (token_ptr[5], NULL, 10);

        if (kernel_loops < 1)
        {
          event_log_warning (hashcat_ctx, "Tuning-db: Invalid kernel_loops '%d' in Line '%d'", kernel_loops, line_num);

          continue;
        }

        if ((user_options_extra->attack_kern == ATTACK_KERN_STRAIGHT) && (kernel_loops > KERNEL_RULES))
        {
          event_log_warning (hashcat_ctx, "Tuning-db: Invalid kernel_loops '%d' in Line '%d'", kernel_loops, line_num);

          continue;
        }

        if ((user_options_extra->attack_kern == ATTACK_KERN_COMBI) && (kernel_loops > KERNEL_COMBS))
        {
          event_log_warning (hashcat_ctx, "Tuning-db: Invalid kernel_loops '%d' in Line '%d'", kernel_loops, line_num);

          continue;
        }

        if ((user_options_extra->attack_kern == ATTACK_KERN_BF) && (kernel_loops > KERNEL_BFS))
        {
          event_log_warning (hashcat_ctx, "Tuning-db: Invalid kernel_loops '%d' in Line '%d'", kernel_loops, line_num);

          continue;
        }
      }

      tuning_db_entry_t *entry = &tuning_db->entry_buf[tuning_db->entry_cnt];

      entry->device_name  = hcstrdup (device_name);
      entry->attack_mode  = attack_mode;
      entry->hash_mode    = hash_mode;
      entry->vector_width = vector_width;
      entry->kernel_accel = kernel_accel;
      entry->kernel_loops = kernel_loops;

      tuning_db->entry_cnt++;
    }
    else
    {
      event_log_warning (hashcat_ctx, "Tuning-db: Invalid number of token in Line '%d'", line_num);

      continue;
    }
  }

  hcfree (buf);

  hc_fclose (&fp);

  // todo: print loaded 'cnt' message

  // sort the database

  qsort (tuning_db->alias_buf, tuning_db->alias_cnt, sizeof (tuning_db_alias_t), sort_by_tuning_db_alias);
  qsort (tuning_db->entry_buf, tuning_db->entry_cnt, sizeof (tuning_db_entry_t), sort_by_tuning_db_entry);

  return 0;
}