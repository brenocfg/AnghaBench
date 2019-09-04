#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int benchmark; int keyspace; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_9__ {int /*<<< orphan*/  hc_hash; } ;
typedef  TYPE_2__ user_options_extra_t ;
struct TYPE_10__ {scalar_t__ hashlist_mode; int /*<<< orphan*/  hashfile; } ;
typedef  TYPE_3__ hashes_t ;
struct TYPE_11__ {int opts_type; } ;
typedef  TYPE_4__ hashconfig_t ;
struct TYPE_12__ {TYPE_2__* user_options_extra; TYPE_1__* user_options; TYPE_3__* hashes; TYPE_4__* hashconfig; } ;
typedef  TYPE_5__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ HL_MODE_ARG ; 
 scalar_t__ HL_MODE_FILE_BINARY ; 
 scalar_t__ HL_MODE_FILE_PLAIN ; 
 int OPTS_TYPE_BINARY_HASHFILE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hc_path_exist (int /*<<< orphan*/ ) ; 
 int hc_path_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int hashes_init_filename (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t         *hashconfig         = hashcat_ctx->hashconfig;
  hashes_t             *hashes             = hashcat_ctx->hashes;
  user_options_t       *user_options       = hashcat_ctx->user_options;
  user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  /**
   * load hashes, part I: find input mode, count hashes
   */

  if (hashconfig->opts_type & OPTS_TYPE_BINARY_HASHFILE)
  {
    hashes->hashlist_mode = HL_MODE_FILE_BINARY;

    if ((user_options->benchmark == false) && (user_options->keyspace == false))
    {
      if (hc_path_read (user_options_extra->hc_hash) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", user_options_extra->hc_hash, strerror (errno));

        return -1;
      }

      hashes->hashfile = user_options_extra->hc_hash;
    }
  }
  else
  {
    hashes->hashlist_mode = (hc_path_exist (user_options_extra->hc_hash) == true) ? HL_MODE_FILE_PLAIN : HL_MODE_ARG;

    if (hashes->hashlist_mode == HL_MODE_FILE_PLAIN)
    {
      hashes->hashfile = user_options_extra->hc_hash;
    }
  }

  return 0;
}