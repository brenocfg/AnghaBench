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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  _DEF_DIRMODE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  getmode (void*,int /*<<< orphan*/ ) ; 
 void* setmode (char*) ; 

__attribute__((used)) static mode_t
validate_mode(char *mode)
{
	mode_t m;
	void *set;

	if ((set = setmode(mode)) == NULL)
		errx(EX_DATAERR, "invalid directory creation mode '%s'", mode);

	m = getmode(set, _DEF_DIRMODE);
	free(set);
	return (m);
}