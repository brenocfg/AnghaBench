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
typedef  int /*<<< orphan*/  zap_name_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int fzap_checkname (int /*<<< orphan*/ *) ; 
 int fzap_checksize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fzap_check(zap_name_t *zn, uint64_t integer_size, uint64_t num_integers)
{
	int err = fzap_checkname(zn);
	if (err != 0)
		return (err);
	return (fzap_checksize(integer_size, num_integers));
}