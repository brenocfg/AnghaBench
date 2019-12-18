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
typedef  char* uintmax_t ;
typedef  scalar_t__ UINT64 ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strtoq (char*,char**,int) ; 

__attribute__((used)) static UINT64
aml_simulate_prompt(char *msg, UINT64 def_val)
{
	char		buf[16], *ep;
	UINT64		val;

	val = def_val;
	printf("DEBUG");
	if (msg != NULL) {
		printf("%s", msg);
	}
	printf("(default: 0x%jx ", (uintmax_t)val);
	printf(" / %ju) >>", (uintmax_t)val);
	fflush(stdout);

	bzero(buf, sizeof buf);
	while (1) {
		if (read(0, buf, sizeof buf) == 0) {
			continue;
		}
		if (buf[0] == '\n') {
			break;	/* use default value */
		}
		if (buf[0] == '0' && buf[1] == 'x') {
			val = strtoq(buf, &ep, 16);
		} else {
			val = strtoq(buf, &ep, 10);
		}
		break;
	}
	return (val);
}