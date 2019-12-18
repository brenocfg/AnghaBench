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
struct filed {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct filed*,int /*<<< orphan*/ ) ; 
 struct filed* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fhead ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static int
addfile(struct filed *f0)
{
	struct filed *f;

	f = calloc(1, sizeof(*f));
	if (f == NULL)
		err(1, "malloc failed");
	*f = *f0;
	STAILQ_INSERT_TAIL(&fhead, f, next);

	return (0);
}