#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dicts_avail; int dicts_cnt; char** dicts; } ;
typedef  TYPE_1__ straight_ctx_t ;
struct TYPE_6__ {TYPE_1__* straight_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int INCR_DICTS ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,char const*) ; 
 int hc_path_has_bom (char const*) ; 
 scalar_t__ hcrealloc (char**,int,int) ; 
 char* hcstrdup (char const*) ; 

__attribute__((used)) static int straight_ctx_add_wl (hashcat_ctx_t *hashcat_ctx, const char *dict)
{
  if (hc_path_has_bom (dict) == true)
  {
    event_log_error (hashcat_ctx, "%s: Byte Order Mark (BOM) was detected", dict);

    return -1;
  }

  straight_ctx_t *straight_ctx = hashcat_ctx->straight_ctx;

  if (straight_ctx->dicts_avail == straight_ctx->dicts_cnt)
  {
    straight_ctx->dicts = (char **) hcrealloc (straight_ctx->dicts, straight_ctx->dicts_avail * sizeof (char *), INCR_DICTS * sizeof (char *));

    straight_ctx->dicts_avail += INCR_DICTS;
  }

  straight_ctx->dicts[straight_ctx->dicts_cnt] = hcstrdup (dict);

  straight_ctx->dicts_cnt++;

  return 0;
}