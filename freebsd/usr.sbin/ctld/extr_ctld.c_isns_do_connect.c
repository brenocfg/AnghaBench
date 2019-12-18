#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct isns {int /*<<< orphan*/  i_addr; TYPE_1__* i_ai; } ;
struct TYPE_2__ {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isns_do_connect(struct isns *isns)
{
	int s;

	s = socket(isns->i_ai->ai_family, isns->i_ai->ai_socktype,
	    isns->i_ai->ai_protocol);
	if (s < 0) {
		log_warn("socket(2) failed for %s", isns->i_addr);
		return (-1);
	}
	if (connect(s, isns->i_ai->ai_addr, isns->i_ai->ai_addrlen)) {
		log_warn("connect(2) failed for %s", isns->i_addr);
		close(s);
		return (-1);
	}
	return(s);
}