#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_17__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  module; } ;
struct TYPE_19__ {scalar_t__ sub_graph; scalar_t__ graph; scalar_t__ data; scalar_t__ protocol; scalar_t__ method; scalar_t__ maxts; scalar_t__ cumts; scalar_t__ avgts; scalar_t__ bw; scalar_t__ percent; scalar_t__ visitors; scalar_t__ hits; } ;
struct TYPE_18__ {scalar_t__ append_protocol; scalar_t__ append_method; scalar_t__ serve_usecs; scalar_t__ bandwidth; } ;
typedef  TYPE_1__ GOutput ;
typedef  int /*<<< orphan*/  GModule ;
typedef  int /*<<< orphan*/  GDashRender ;
typedef  TYPE_2__ GDashModule ;

/* Variables and functions */
 TYPE_17__ conf ; 
 int get_xpos () ; 
 TYPE_1__* output_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_avgts (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_bars (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_bw (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_cumts (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_data (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_hits (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_hits_percent (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_maxts (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_method (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_proto (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_visitors (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  render_visitors_percent (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
render_metrics (GDashModule * data, GDashRender render, int expanded)
{
  int x = get_xpos ();
  GModule module = data->module;
  const GOutput *output = output_lookup (module);

  /* basic metrics */
  if (output->hits)
    render_hits (data, render, &x);
  if (output->percent)
    render_hits_percent (data, render, &x);
  if (output->visitors)
    render_visitors (data, render, &x);
  if (output->percent)
    render_visitors_percent (data, render, &x);

  /* render bandwidth if available */
  if (conf.bandwidth && output->bw)
    render_bw (data, render, &x);

  /* render avgts, cumts and maxts if available */
  if (output->avgts && conf.serve_usecs)
    render_avgts (data, render, &x);
  if (output->cumts && conf.serve_usecs)
    render_cumts (data, render, &x);
  if (output->maxts && conf.serve_usecs)
    render_maxts (data, render, &x);

  /* render request method if available */
  if (output->method && conf.append_method)
    render_method (data, render, &x);
  /* render request protocol if available */
  if (output->protocol && conf.append_protocol)
    render_proto (data, render, &x);
  if (output->data)
    render_data (data, render, &x);

  /* skip graph bars if module is expanded and we have sub nodes */
  if ((output->graph && !expanded) || (output->sub_graph && expanded))
    render_bars (data, render, &x);
}