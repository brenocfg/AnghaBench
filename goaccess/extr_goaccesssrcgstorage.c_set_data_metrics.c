#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  nts; } ;
struct TYPE_15__ {int /*<<< orphan*/  nts; } ;
struct TYPE_14__ {int /*<<< orphan*/  nts; } ;
struct TYPE_13__ {scalar_t__ nbw; } ;
struct TYPE_18__ {scalar_t__ hits; scalar_t__ visitors; float hits_perc; float bw_perc; float visitors_perc; int /*<<< orphan*/  data; scalar_t__ protocol; scalar_t__ method; TYPE_4__ maxts; TYPE_3__ cumts; TYPE_2__ avgts; TYPE_1__ bw; int /*<<< orphan*/  id; } ;
struct TYPE_17__ {int /*<<< orphan*/  bw; int /*<<< orphan*/  visitors; int /*<<< orphan*/  hits; } ;
struct TYPE_12__ {scalar_t__ append_protocol; scalar_t__ append_method; scalar_t__ serve_usecs; } ;
typedef  TYPE_5__ GPercTotals ;
typedef  TYPE_6__ GMetrics ;

/* Variables and functions */
 TYPE_11__ conf ; 
 float get_percentage (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_6__* new_gmetrics () ; 

void
set_data_metrics (GMetrics * ometrics, GMetrics ** nmetrics, GPercTotals totals)
{
  GMetrics *metrics;

  /* determine percentages for certain fields */
  float hits_perc = get_percentage (totals.hits, ometrics->hits);
  float visitors_perc = get_percentage (totals.visitors, ometrics->visitors);
  float bw_perc = get_percentage (totals.bw, ometrics->bw.nbw);

  metrics = new_gmetrics ();

  /* basic fields */
  metrics->id = ometrics->id;
  metrics->hits = ometrics->hits;
  metrics->visitors = ometrics->visitors;

  /* percentage fields */
  metrics->hits_perc = hits_perc < 0 ? 0 : hits_perc;
  metrics->bw_perc = bw_perc < 0 ? 0 : bw_perc;
  metrics->visitors_perc = visitors_perc < 0 ? 0 : visitors_perc;

  /* bandwidth field */
  metrics->bw.nbw = ometrics->bw.nbw;

  /* time served fields */
  if (conf.serve_usecs && ometrics->hits > 0) {
    metrics->avgts.nts = ometrics->avgts.nts;
    metrics->cumts.nts = ometrics->cumts.nts;
    metrics->maxts.nts = ometrics->maxts.nts;
  }

  /* method field */
  if (conf.append_method && ometrics->method)
    metrics->method = ometrics->method;

  /* protocol field */
  if (conf.append_protocol && ometrics->protocol)
    metrics->protocol = ometrics->protocol;

  /* data field */
  metrics->data = ometrics->data;

  *nmetrics = metrics;
}