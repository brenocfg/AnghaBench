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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int handle_data (int,char*,int) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 

void handle_dude(int dude, int raw)
{
	char buf[4096];
	int rd;

	while (1) {
		rd = recv(raw, buf, sizeof(buf), 0);
		if (rd == -1)
			err(1, "recv()");
		
		if (handle_data(dude, buf, rd) == -1)
			return;
	}
}