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
typedef  int /*<<< orphan*/  nlm4_stats ;

/* Variables and functions */
 int EROFS ; 
 int ESTALE ; 
 int /*<<< orphan*/  nlm4_failed ; 
 int /*<<< orphan*/  nlm4_rofs ; 
 int /*<<< orphan*/  nlm4_stale_fh ; 

__attribute__((used)) static nlm4_stats
nlm_convert_error(int error)
{

	if (error == ESTALE)
		return nlm4_stale_fh;
	else if (error == EROFS)
		return nlm4_rofs;
	else
		return nlm4_failed;
}