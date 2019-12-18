#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nk_context {int dummy; } ;
struct nk_color {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  NK_CHART_LINES ; 
 scalar_t__ nk_chart_begin_colored (struct nk_context*,int /*<<< orphan*/ ,struct nk_color,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_chart_end (struct nk_context*) ; 
 scalar_t__ nk_chart_push (struct nk_context*,unsigned short) ; 
 int /*<<< orphan*/  nk_rgb (int,int,int) ; 
 int /*<<< orphan*/  nk_tooltip (struct nk_context*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,unsigned short,unsigned short) ; 

__attribute__((used)) static void chart_ramp_array(struct nk_context* nk,
                             struct nk_color color,
                             int count, unsigned short int* values)
{
    if (nk_chart_begin_colored(nk, NK_CHART_LINES,
                               color, nk_rgb(255, 255, 255),
                               count, 0, 65535))
    {
        int i;
        for (i = 0;  i < count;  i++)
        {
            char buffer[1024];
            if (nk_chart_push(nk, values[i]))
            {
                snprintf(buffer, sizeof(buffer), "#%u: %u (%0.5f) ",
                         i, values[i], values[i] / 65535.f);
                nk_tooltip(nk, buffer);
            }
        }

        nk_chart_end(nk);
    }
}