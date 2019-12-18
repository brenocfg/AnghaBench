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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  con_sock ; 
 int /*<<< orphan*/  gmtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
http_date(void)
{
	time_t	tl;
	char	buff[50];

	tl = time(NULL);
	strftime(buff, 50, "Date: %a, %d %h %Y %H:%M:%S %Z\r\n", gmtime(&tl));
	write(con_sock, buff, strlen(buff));
	/* return(buff); */
}