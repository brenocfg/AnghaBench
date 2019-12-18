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
typedef  int /*<<< orphan*/  version ;
typedef  int uint8_t ;
struct acctv3 {int dummy; } ;
typedef  int /*<<< orphan*/  magic ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EFTYPE ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fread_record (int*,int,int /*<<< orphan*/ *) ; 
 int readrec_v2 (int /*<<< orphan*/ *,struct acctv3*) ; 
 int readrec_v3 (int /*<<< orphan*/ *,struct acctv3*) ; 
 scalar_t__ ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
readrec_vx(FILE *f, struct acctv3 *av3)
{
	uint8_t magic, version;

	if (fread_record(&magic, sizeof(magic), f) == EOF ||
	    fread_record(&version, sizeof(version), f) == EOF ||
	    ungetc(version, f) == EOF ||
	    ungetc(magic, f) == EOF)
		return (EOF);
	switch (version) {
	case 2:
		return (readrec_v2(f, av3));
	case 3:
		return (readrec_v3(f, av3));

	/* Add handling for more versions here. */

	default:
		errno = EFTYPE;
		return (EOF);
	}
}