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
struct pdu {int /*<<< orphan*/  pdu_connection; } ;

/* Variables and functions */
 struct pdu* pdu_new (int /*<<< orphan*/ ) ; 

struct pdu *
pdu_new_response(struct pdu *request)
{

	return (pdu_new(request->pdu_connection));
}