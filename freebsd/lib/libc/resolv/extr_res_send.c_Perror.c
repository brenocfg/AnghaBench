#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* res_state ;
struct TYPE_3__ {unsigned int options; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int RES_DEBUG ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 char* strerror (int) ; 

__attribute__((used)) static void
Perror(const res_state statp, FILE *file, const char *string, int error) {
	int save = errno;

	if ((statp->options & RES_DEBUG) != 0U)
		fprintf(file, "res_send: %s: %s\n",
			string, strerror(error));
	errno = save;
}