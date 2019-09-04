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
struct gkc_summary {int dummy; } ;

/* Variables and functions */
 struct gkc_summary* calloc (int,int) ; 
 int /*<<< orphan*/  gkc_summary_init (struct gkc_summary*,double) ; 

struct gkc_summary *gkc_summary_alloc(double epsilon)
{
    struct gkc_summary *s;
    s = calloc(1, sizeof(*s));
    gkc_summary_init(s, epsilon);
    return s;
}