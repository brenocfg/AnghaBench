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
struct smb_bitname {int bn_bit; char* bn_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

char *
smb_printb(char *dest, int flags, const struct smb_bitname *bnp) {
	int first = 1;

	strcpy(dest, "<");
	for(; bnp->bn_bit; bnp++) {
		if (flags & bnp->bn_bit) {
			strcat(dest, bnp->bn_name);
			first = 0;
		}
		if (!first && (flags & bnp[1].bn_bit))
			strcat(dest, "|");
	}
	strcat(dest, ">");
	return dest;
}