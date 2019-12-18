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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (char*,char*,...) ; 
 char* sldns_wire2str_dname (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
print_id(FILE* out, char* fname, uint8_t* nm, size_t nmlen, uint16_t dclass)
{
	char* s = sldns_wire2str_dname(nm, nmlen);
	if(!s) {
		log_err("malloc failure in write to %s", fname);
		return 0;
	}
	if(fprintf(out, ";;id: %s %d\n", s, (int)dclass) < 0) {
		log_err("could not write to %s: %s", fname, strerror(errno));
		free(s);
		return 0;
	}
	free(s);
	return 1;
}