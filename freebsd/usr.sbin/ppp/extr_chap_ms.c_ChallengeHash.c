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
typedef  int /*<<< orphan*/  SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1_Final (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ *,char*,int) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
ChallengeHash(char *PeerChallenge, char *AuthenticatorChallenge,
              char *UserName, char *Challenge)
{
  SHA_CTX Context;
  char Digest[SHA_DIGEST_LENGTH];
  char *Name;

  Name = strrchr(UserName, '\\');
  if(NULL == Name)
    Name = UserName;
  else
    Name++;

  SHA1_Init(&Context);

  SHA1_Update(&Context, PeerChallenge, 16);
  SHA1_Update(&Context, AuthenticatorChallenge, 16);
  SHA1_Update(&Context, Name, strlen(Name));

  SHA1_Final(Digest, &Context);
  memcpy(Challenge, Digest, 8);
}