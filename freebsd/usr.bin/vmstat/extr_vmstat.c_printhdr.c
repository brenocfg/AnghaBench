#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u_long ;
struct TYPE_2__ {scalar_t__ selected; int /*<<< orphan*/  unit_number; int /*<<< orphan*/ * device_name; } ;

/* Variables and functions */
 int MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Pflag ; 
 TYPE_1__* dev_select ; 
 int /*<<< orphan*/  doresize () ; 
 int /*<<< orphan*/  hdrcnt ; 
 scalar_t__ hflag ; 
 scalar_t__ maxshowdevs ; 
 int num_devices ; 
 int /*<<< orphan*/  num_selected ; 
 int /*<<< orphan*/  winlines ; 
 scalar_t__ wresized ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 

__attribute__((used)) static void
printhdr(int maxid, u_long cpumask)
{
	int i, num_shown;

	num_shown = MIN(num_selected, maxshowdevs);
	if (hflag)
		xo_emit(" {T:procs}    {T:memory}    {T:/page%*s}", 19, "");
	else
		xo_emit("{T:procs}     {T:memory}       {T:/page%*s}", 19, "");
	if (num_shown > 1)
		xo_emit("   {T:/disks %*s}  ", num_shown * 4 - 7, "");
	else if (num_shown == 1)
		xo_emit("   {T:disks}");
	xo_emit(" {T:faults}      ");
	if (Pflag) {
		for (i = 0; i <= maxid; i++) {
			if (cpumask & (1ul << i))
				xo_emit("  {T:/cpu%d}   ", i);
		}
		xo_emit("\n");
	} else
		xo_emit(" {T:cpu}\n");
	if (hflag) {
		xo_emit(" {T:r}  {T:b}  {T:w}  {T:avm}  {T:fre}  {T:flt}  {T:re}"
		    "  {T:pi}  {T:po}   {T:fr}   {T:sr} ");
	} else {
		xo_emit("{T:r} {T:b} {T:w}     {T:avm}     {T:fre}  {T:flt}  "
		    "{T:re}  {T:pi}  {T:po}    {T:fr}   {T:sr} ");
	}
	for (i = 0; i < num_devices; i++)
		if ((dev_select[i].selected) &&
		    (dev_select[i].selected <= maxshowdevs))
			xo_emit("{T:/%c%c%d} ", dev_select[i].device_name[0],
			    dev_select[i].device_name[1],
			    dev_select[i].unit_number);
	xo_emit("  {T:in}   {T:sy}   {T:cs}");
	if (Pflag) {
		for (i = 0; i <= maxid; i++) {
			if (cpumask & (1ul << i))
				xo_emit(" {T:us} {T:sy} {T:id}");
		}
		xo_emit("\n");
	} else
		xo_emit(" {T:us} {T:sy} {T:id}\n");
	if (wresized != 0)
		doresize();
	hdrcnt = winlines;
}