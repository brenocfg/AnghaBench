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
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_type_values ; 
 char* tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
print_btp_body(netdissect_options *ndo,
               const u_char *bp)
{
	int version;
	int msg_type;
	const char *msg_type_str;

	/* Assuming ItsDpuHeader */
	version = bp[0];
	msg_type = bp[1];
	msg_type_str = tok2str(msg_type_values, "unknown (%u)", msg_type);

	ND_PRINT((ndo, "; ItsPduHeader v:%d t:%d-%s", version, msg_type, msg_type_str));
}