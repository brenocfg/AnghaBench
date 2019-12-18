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
struct sockaddr_dl {int sdl_len; scalar_t__ sdl_alen; } ;
typedef  int /*<<< orphan*/  sdl ;

/* Variables and functions */
 scalar_t__ IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  link_addr (char*,struct sockaddr_dl*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  set80211 (int,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
set80211macmac(int s, int op, const char *val)
{
	char *temp;
	struct sockaddr_dl sdl;

	temp = malloc(strlen(val) + 2); /* ':' and '\0' */
	if (temp == NULL)
		errx(1, "malloc failed");
	temp[0] = ':';
	strcpy(temp + 1, val);
	sdl.sdl_len = sizeof(sdl);
	link_addr(temp, &sdl);
	free(temp);
	if (sdl.sdl_alen != IEEE80211_ADDR_LEN)
		errx(1, "malformed link-level address");
	set80211(s, op, 0, IEEE80211_ADDR_LEN, LLADDR(&sdl));
}