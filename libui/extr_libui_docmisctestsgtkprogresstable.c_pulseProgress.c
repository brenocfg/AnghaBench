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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_PROGRESS_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_progress_bar_pulse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progressbar ; 

__attribute__((used)) static gboolean pulseProgress(gpointer data)
{
	gtk_progress_bar_pulse(GTK_PROGRESS_BAR(progressbar));
	return TRUE;
}