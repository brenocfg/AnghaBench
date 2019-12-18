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
typedef  int /*<<< orphan*/  uintmax_t ;
struct suj_ino {struct jtrncrec* si_trunc; } ;
struct jtrncrec {int jt_op; scalar_t__ jt_size; scalar_t__ jt_ino; } ;

/* Variables and functions */
 scalar_t__ JOP_SYNC ; 
 scalar_t__ debug ; 
 struct suj_ino* ino_lookup (scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ino_build_trunc(struct jtrncrec *rec)
{
	struct suj_ino *sino;

	if (debug)
		printf("ino_build_trunc: op %d ino %ju, size %jd\n",
		    rec->jt_op, (uintmax_t)rec->jt_ino,
		    (uintmax_t)rec->jt_size);
	sino = ino_lookup(rec->jt_ino, 1);
	if (rec->jt_op == JOP_SYNC) {
		sino->si_trunc = NULL;
		return;
	}
	if (sino->si_trunc == NULL || sino->si_trunc->jt_size > rec->jt_size)
		sino->si_trunc = rec;
}