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
typedef  int /*<<< orphan*/  u_char ;
struct rx_header {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  AFSNAMEMAX ; 
 int /*<<< orphan*/  AFSOPAQUEMAX ; 
 int /*<<< orphan*/  DATEOUT () ; 
 unsigned long EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  FIDOUT () ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 scalar_t__ RX_PACKET_TYPE_ABORT ; 
 scalar_t__ RX_PACKET_TYPE_DATA ; 
 int /*<<< orphan*/  STROUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  afs_fs_errors ; 
 int /*<<< orphan*/  fs_req ; 
 unsigned long min (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,unsigned long) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static void
fs_reply_print(netdissect_options *ndo,
               register const u_char *bp, int length, int32_t opcode)
{
	unsigned long i;
	const struct rx_header *rxh;

	if (length <= (int)sizeof(struct rx_header))
		return;

	rxh = (const struct rx_header *) bp;

	/*
	 * Print out the afs call we're invoking.  The table used here was
	 * gleaned from fsint/afsint.xg
	 */

	ND_PRINT((ndo, " fs reply %s", tok2str(fs_req, "op#%d", opcode)));

	bp += sizeof(struct rx_header);

	/*
	 * If it was a data packet, interpret the response
	 */

	if (rxh->type == RX_PACKET_TYPE_DATA) {
		switch (opcode) {
		case 131:	/* Fetch ACL */
		{
			char a[AFSOPAQUEMAX+1];
			ND_TCHECK2(bp[0], 4);
			i = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			ND_TCHECK2(bp[0], i);
			i = min(AFSOPAQUEMAX, i);
			strncpy(a, (const char *) bp, i);
			a[i] = '\0';
			acl_print(ndo, (u_char *) a, sizeof(a), (u_char *) a + i);
			break;
		}
		case 137:	/* Create file */
		case 141:	/* MakeDir */
			ND_PRINT((ndo, " new"));
			FIDOUT();
			break;
		case 151:	/* Get root volume */
			ND_PRINT((ndo, " root volume"));
			STROUT(AFSNAMEMAX);
			break;
		case 153:	/* Get time */
			DATEOUT();
			break;
		default:
			;
		}
	} else if (rxh->type == RX_PACKET_TYPE_ABORT) {
		/*
		 * Otherwise, just print out the return code
		 */
		ND_TCHECK2(bp[0], sizeof(int32_t));
		i = (int) EXTRACT_32BITS(bp);
		bp += sizeof(int32_t);

		ND_PRINT((ndo, " error %s", tok2str(afs_fs_errors, "#%d", i)));
	} else {
		ND_PRINT((ndo, " strange fs reply of type %d", rxh->type));
	}

	return;

trunc:
	ND_PRINT((ndo, " [|fs]"));
}