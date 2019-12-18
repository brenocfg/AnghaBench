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
typedef  char u_char ;

/* Variables and functions */
 int /*<<< orphan*/  ChallengeResponse (char*,char*,char*) ; 
 int /*<<< orphan*/  DesEncrypt (char*,char*,char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 char toupper (char) ; 

void
mschap_LANMan(char *digest, char *challenge, char *secret)
{
  static u_char salt[] = "KGS!@#$%";	/* RASAPI32.dll */
  char SECRET[14], *ptr, *end;
  u_char hash[16];

  end = SECRET + sizeof SECRET;
  for (ptr = SECRET; *secret && ptr < end; ptr++, secret++)
    *ptr = toupper(*secret);
  if (ptr < end)
    memset(ptr, '\0', end - ptr);

  DesEncrypt(salt, SECRET, hash);
  DesEncrypt(salt, SECRET + 7, hash + 8);

  ChallengeResponse(challenge, hash, digest);
}