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
typedef  int /*<<< orphan*/  u8 ;
struct x509_name {int /*<<< orphan*/  rid; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  asn1_oid_to_str (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ asn1_parse_oid (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int x509_parse_alt_name_rid(struct x509_name *name,
				   const u8 *pos, size_t len)
{
	char buf[80];

	/* registeredID OBJECT IDENTIFIER */
	if (asn1_parse_oid(pos, len, &name->rid) < 0)
		return -1;

	asn1_oid_to_str(&name->rid, buf, sizeof(buf));
	wpa_printf(MSG_MSGDUMP, "X509: altName - registeredID: %s", buf);

	return 0;
}