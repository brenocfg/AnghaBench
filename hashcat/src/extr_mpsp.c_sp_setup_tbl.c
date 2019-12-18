#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* markov_hcstat2; void* markov_classic; void* markov_disable; } ;
typedef  TYPE_1__ user_options_t ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
typedef  void* u32 ;
struct stat {scalar_t__ st_size; } ;
struct TYPE_10__ {TYPE_3__* markov_table_buf; TYPE_3__* root_table_buf; } ;
typedef  TYPE_2__ mask_ctx_t ;
typedef  int /*<<< orphan*/  hcstat_tmp ;
struct TYPE_11__ {scalar_t__ val; void* key; } ;
typedef  TYPE_3__ hcstat_table_t ;
struct TYPE_12__ {TYPE_1__* user_options; TYPE_2__* mask_ctx; TYPE_5__* folder_config; } ;
typedef  TYPE_4__ hashcat_ctx_t ;
struct TYPE_13__ {char* shared_dir; } ;
typedef  TYPE_5__ folder_config_t ;
typedef  scalar_t__ SizeT ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 int CHARSIZ ; 
 scalar_t__ SP_FILESZ ; 
 char* SP_HCSTAT ; 
 int SP_MARKOV_CNT ; 
 int SP_PW_MAX ; 
 int SP_ROOT_CNT ; 
 scalar_t__ SP_VERSION ; 
 scalar_t__ const SZ_OK ; 
 scalar_t__ byte_swap_64 (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_4__*,char*,char*,...) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ hc_fread (scalar_t__*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ hc_lzma2_decompress (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,char const*) ; 
 scalar_t__ hccalloc (int,int) ; 
 int /*<<< orphan*/  hcfree (scalar_t__*) ; 
 scalar_t__ hcmalloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsort (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  sp_comp_val ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sp_setup_tbl (hashcat_ctx_t *hashcat_ctx)
{
  folder_config_t *folder_config = hashcat_ctx->folder_config;
  mask_ctx_t      *mask_ctx      = hashcat_ctx->mask_ctx;
  user_options_t  *user_options  = hashcat_ctx->user_options;

  char *shared_dir = folder_config->shared_dir;

  char *hcstat  = user_options->markov_hcstat2;
  u32   disable = user_options->markov_disable;
  u32   classic = user_options->markov_classic;

  hcstat_table_t *root_table_buf   = mask_ctx->root_table_buf;
  hcstat_table_t *markov_table_buf = mask_ctx->markov_table_buf;

  /**
   * Initialize hcstats
   */

  u64 *root_stats_buf = (u64 *) hccalloc (SP_ROOT_CNT, sizeof (u64));

  u64 *root_stats_ptr = root_stats_buf;

  u64 *root_stats_buf_by_pos[SP_PW_MAX];

  for (int i = 0; i < SP_PW_MAX; i++)
  {
    root_stats_buf_by_pos[i] = root_stats_ptr;

    root_stats_ptr += CHARSIZ;
  }

  u64 *markov_stats_buf = (u64 *) hccalloc (SP_MARKOV_CNT, sizeof (u64));

  u64 *markov_stats_ptr = markov_stats_buf;

  u64 *markov_stats_buf_by_key[SP_PW_MAX][CHARSIZ];

  for (int i = 0; i < SP_PW_MAX; i++)
  {
    for (int j = 0; j < CHARSIZ; j++)
    {
      markov_stats_buf_by_key[i][j] = markov_stats_ptr;

      markov_stats_ptr += CHARSIZ;
    }
  }

  /**
   * Load hcstats File
   */

  char hcstat_tmp[256];

  if (hcstat == NULL)
  {
    snprintf (hcstat_tmp, sizeof (hcstat_tmp), "%s/%s", shared_dir, SP_HCSTAT);

    hcstat = hcstat_tmp;
  }

  struct stat s;

  if (stat (hcstat, &s) == -1)
  {
    event_log_error (hashcat_ctx, "%s: %s", hcstat, strerror (errno));

    return -1;
  }

  HCFILE fp;

  if (hc_fopen (&fp, hcstat, "rb") == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", hcstat, strerror (errno));

    return -1;
  }

  u8 *inbuf = (u8 *) hcmalloc (s.st_size);

  SizeT inlen = (SizeT) hc_fread (inbuf, 1, s.st_size, &fp);

  if (inlen != (SizeT) s.st_size)
  {
    event_log_error (hashcat_ctx, "%s: Could not read data.", hcstat);

    hc_fclose (&fp);

    hcfree (inbuf);

    return -1;
  }

  hc_fclose (&fp);

  u8 *outbuf = (u8 *) hcmalloc (SP_FILESZ);

  SizeT outlen = SP_FILESZ;

  const char props = 0x1c; // lzma properties constant, retrieved with 7z2hashcat

  const SRes res = hc_lzma2_decompress (inbuf, &inlen, outbuf, &outlen, &props);

  if (res != SZ_OK)
  {
    event_log_error (hashcat_ctx, "%s: Could not uncompress data.", hcstat);

    hcfree (inbuf);
    hcfree (outbuf);

    return -1;
  }

  if (outlen != SP_FILESZ)
  {
    event_log_error (hashcat_ctx, "%s: Could not uncompress data.", hcstat);

    hcfree (inbuf);
    hcfree (outbuf);

    return -1;
  }

  u64 *ptr = (u64 *) outbuf;

  u64 v = *ptr++;
  u64 z = *ptr++;

  memcpy (root_stats_buf,   ptr, sizeof (u64) * SP_ROOT_CNT);   ptr += SP_ROOT_CNT;
  memcpy (markov_stats_buf, ptr, sizeof (u64) * SP_MARKOV_CNT); // ptr += SP_MARKOV_CNT;

  hcfree (inbuf);
  hcfree (outbuf);

  /**
   * switch endianess
   */

  v = byte_swap_64 (v);
  z = byte_swap_64 (z);

  for (int i = 0; i < SP_ROOT_CNT; i++)   root_stats_buf[i]   = byte_swap_64 (root_stats_buf[i]);
  for (int i = 0; i < SP_MARKOV_CNT; i++) markov_stats_buf[i] = byte_swap_64 (markov_stats_buf[i]);

  /**
   * verify header
   */

  if (v != SP_VERSION)
  {
    event_log_error (hashcat_ctx, "%s: Invalid header", hcstat);

    return -1;
  }

  if (z != 0)
  {
    event_log_error (hashcat_ctx, "%s: Invalid header", hcstat);

    return -1;
  }

  /**
   * Markov modifier of hcstat_table on user request
   */

  if (disable)
  {
    memset (root_stats_buf,   0, SP_ROOT_CNT   * sizeof (u64));
    memset (markov_stats_buf, 0, SP_MARKOV_CNT * sizeof (u64));
  }

  if (classic)
  {
    /* Add all stats to first position */

    for (int i = 1; i < SP_PW_MAX; i++)
    {
      u64 *out = root_stats_buf_by_pos[0];
      u64 *in  = root_stats_buf_by_pos[i];

      for (int j = 0; j < CHARSIZ; j++)
      {
        *out++ += *in++;
      }
    }

    for (int i = 1; i < SP_PW_MAX; i++)
    {
      u64 *out = markov_stats_buf_by_key[0][0];
      u64 *in  = markov_stats_buf_by_key[i][0];

      for (int j = 0; j < CHARSIZ; j++)
      {
        for (int k = 0; k < CHARSIZ; k++)
        {
          *out++ += *in++;
        }
      }
    }

    /* copy them to all pw_positions */

    for (int i = 1; i < SP_PW_MAX; i++)
    {
      memcpy (root_stats_buf_by_pos[i], root_stats_buf_by_pos[0], CHARSIZ * sizeof (u64));
    }

    for (int i = 1; i < SP_PW_MAX; i++)
    {
      memcpy (markov_stats_buf_by_key[i][0], markov_stats_buf_by_key[0][0], CHARSIZ * CHARSIZ * sizeof (u64));
    }
  }

  /**
   * Initialize tables
   */

  hcstat_table_t *root_table_ptr = root_table_buf;

  hcstat_table_t *root_table_buf_by_pos[SP_PW_MAX];

  for (int i = 0; i < SP_PW_MAX; i++)
  {
    root_table_buf_by_pos[i] = root_table_ptr;

    root_table_ptr += CHARSIZ;
  }

  hcstat_table_t *markov_table_ptr = markov_table_buf;

  hcstat_table_t *markov_table_buf_by_key[SP_PW_MAX][CHARSIZ];

  for (int i = 0; i < SP_PW_MAX; i++)
  {
    for (int j = 0; j < CHARSIZ; j++)
    {
      markov_table_buf_by_key[i][j] = markov_table_ptr;

      markov_table_ptr += CHARSIZ;
    }
  }

  /**
   * Convert hcstat to tables
   */

  for (int i = 0; i < SP_ROOT_CNT; i++)
  {
    u32 key = i % CHARSIZ;

    root_table_buf[i].key = key;
    root_table_buf[i].val = root_stats_buf[i];
  }

  for (int i = 0; i < SP_MARKOV_CNT; i++)
  {
    u32 key = i % CHARSIZ;

    markov_table_buf[i].key = key;
    markov_table_buf[i].val = markov_stats_buf[i];
  }

  hcfree (root_stats_buf);
  hcfree (markov_stats_buf);

  /**
   * Finally sort them
   */

  for (int i = 0; i < SP_PW_MAX; i++)
  {
    qsort (root_table_buf_by_pos[i], CHARSIZ, sizeof (hcstat_table_t), sp_comp_val);
  }

  for (int i = 0; i < SP_PW_MAX; i++)
  {
    for (int j = 0; j < CHARSIZ; j++)
    {
      qsort (markov_table_buf_by_key[i][j], CHARSIZ, sizeof (hcstat_table_t), sp_comp_val);
    }
  }

  return 0;
}