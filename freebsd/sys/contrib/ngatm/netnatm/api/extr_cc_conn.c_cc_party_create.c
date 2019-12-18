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
typedef  void* u_int ;
struct TYPE_4__ {void* epref; void* flag; } ;
struct ccparty {struct ccconn* conn; TYPE_2__ epref; int /*<<< orphan*/  state; } ;
struct ccconn {TYPE_1__* cc; int /*<<< orphan*/  parties; } ;
struct TYPE_3__ {int log; } ;

/* Variables and functions */
 int CCLOG_PARTY_INST ; 
 struct ccparty* CCZALLOC (int) ; 
 int /*<<< orphan*/  IE_SETPRESENT (TYPE_2__) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ccparty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARTY_NULL ; 
 int /*<<< orphan*/  cc_party_log (struct ccparty*,char*,void*,void*) ; 
 int /*<<< orphan*/  link ; 

struct ccparty *
cc_party_create(struct ccconn *conn, u_int ident, u_int flag)
{
	struct ccparty *party;

	party = CCZALLOC(sizeof(*party));
	if (party == NULL)
		return (NULL);

	party->conn = conn;
	party->state = PARTY_NULL;
	IE_SETPRESENT(party->epref);
	party->epref.flag = flag;
	party->epref.epref = ident;
	LIST_INSERT_HEAD(&conn->parties, party, link);

	if (party->conn->cc->log & CCLOG_PARTY_INST)
		cc_party_log(party, "created %u.%u", flag, ident);

	return (party);
}