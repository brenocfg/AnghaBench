#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct pkt {TYPE_2__ sa4; int /*<<< orphan*/  refid; } ;
struct kod_entry {int /*<<< orphan*/  type; } ;
typedef  struct pkt sockaddr_u ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int KOD_DEMOBILIZE ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_MEMORY (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZERO (struct pkt) ; 
 int /*<<< orphan*/  handle_pkt (int,struct pkt*,struct pkt*,char const*) ; 
 int /*<<< orphan*/  inet_addr (char const*) ; 
 int /*<<< orphan*/  kod_init_kod_db (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  search_entry (char const*,struct kod_entry**) ; 

void
test_HandleKodDemobilize(void)
{
	static const char *	HOSTNAME = "192.0.2.1";
	static const char *	REASON = "DENY";
	struct pkt		rpkt;
	sockaddr_u		host;
	int			rpktl;
	struct kod_entry *	entry;

	rpktl = KOD_DEMOBILIZE;
	ZERO(rpkt);
	memcpy(&rpkt.refid, REASON, 4);
	ZERO(host);
	host.sa4.sin_family = AF_INET;
	host.sa4.sin_addr.s_addr = inet_addr(HOSTNAME);

	/* Test that the KOD-entry is added to the database. */
	kod_init_kod_db("/dev/null", TRUE);

	TEST_ASSERT_EQUAL(1, handle_pkt(rpktl, &rpkt, &host, HOSTNAME));

	TEST_ASSERT_EQUAL(1, search_entry(HOSTNAME, &entry));
	TEST_ASSERT_EQUAL_MEMORY(REASON, entry->type, 4);
}