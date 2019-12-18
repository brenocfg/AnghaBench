#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_10__ {TYPE_2__* cpt_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
struct TYPE_11__ {scalar_t__ const cpt_start; } ;
typedef  TYPE_2__ cpt_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_asprintf (char**,char*,int const,int const,int const,...) ; 
 int status_get_cpt_avg_day (TYPE_1__ const*) ; 
 int status_get_cpt_avg_hour (TYPE_1__ const*) ; 
 int status_get_cpt_avg_min (TYPE_1__ const*) ; 
 int status_get_cpt_cur_day (TYPE_1__ const*) ; 
 int status_get_cpt_cur_hour (TYPE_1__ const*) ; 
 int status_get_cpt_cur_min (TYPE_1__ const*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

char *status_get_cpt (const hashcat_ctx_t *hashcat_ctx)
{
  const cpt_ctx_t *cpt_ctx = hashcat_ctx->cpt_ctx;

  const time_t now = time (NULL);

  char *cpt;

  const int cpt_cur_min  = status_get_cpt_cur_min  (hashcat_ctx);
  const int cpt_cur_hour = status_get_cpt_cur_hour (hashcat_ctx);
  const int cpt_cur_day  = status_get_cpt_cur_day  (hashcat_ctx);

  const int cpt_avg_min  = status_get_cpt_avg_min  (hashcat_ctx);
  const int cpt_avg_hour = status_get_cpt_avg_hour (hashcat_ctx);
  const int cpt_avg_day  = status_get_cpt_avg_day  (hashcat_ctx);

  if ((cpt_ctx->cpt_start + 86400) < now)
  {
    hc_asprintf (&cpt, "CUR:%d,%d,%d AVG:%d,%d,%d (Min,Hour,Day)",
      cpt_cur_min,
      cpt_cur_hour,
      cpt_cur_day,
      cpt_avg_min,
      cpt_avg_hour,
      cpt_avg_day);
  }
  else if ((cpt_ctx->cpt_start + 3600) < now)
  {
    hc_asprintf (&cpt, "CUR:%d,%d,N/A AVG:%d,%d,%d (Min,Hour,Day)",
      cpt_cur_min,
      cpt_cur_hour,
      cpt_avg_min,
      cpt_avg_hour,
      cpt_avg_day);
  }
  else if ((cpt_ctx->cpt_start + 60) < now)
  {
    hc_asprintf (&cpt, "CUR:%d,N/A,N/A AVG:%d,%d,%d (Min,Hour,Day)",
      cpt_cur_min,
      cpt_avg_min,
      cpt_avg_hour,
      cpt_avg_day);
  }
  else
  {
    hc_asprintf (&cpt, "CUR:N/A,N/A,N/A AVG:%d,%d,%d (Min,Hour,Day)",
      cpt_avg_min,
      cpt_avg_hour,
      cpt_avg_day);
  }

  return cpt;
}