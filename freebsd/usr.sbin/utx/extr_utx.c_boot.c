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
struct utmpx {short ut_type; int /*<<< orphan*/  ut_tv; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * pututxline (struct utmpx*) ; 

__attribute__((used)) static int
boot(short type)
{
	struct utmpx utx = { .ut_type = type };

	(void)gettimeofday(&utx.ut_tv, NULL);
	if (pututxline(&utx) == NULL) {
		perror("pututxline");
		return (1);
	}
	return (0);
}