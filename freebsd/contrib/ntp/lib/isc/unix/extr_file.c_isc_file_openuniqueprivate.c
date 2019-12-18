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
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  isc_file_openuniquemode (char*,int,int /*<<< orphan*/ **) ; 

isc_result_t
isc_file_openuniqueprivate(char *templet, FILE **fp) {
	int mode = S_IWUSR|S_IRUSR;
	return (isc_file_openuniquemode(templet, mode, fp));
}