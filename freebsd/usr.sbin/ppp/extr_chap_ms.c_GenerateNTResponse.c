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

/* Variables and functions */
 int /*<<< orphan*/  ChallengeHash (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  ChallengeResponse (char*,char*,char*) ; 
 int /*<<< orphan*/  NtPasswordHash (char*,int,char*) ; 

void
GenerateNTResponse(char *AuthenticatorChallenge, char *PeerChallenge,
                   char *UserName, char *Password,
                   int PasswordLen, char *Response)
{
  char Challenge[8];
  char PasswordHash[16];

  ChallengeHash(PeerChallenge, AuthenticatorChallenge, UserName, Challenge);
  NtPasswordHash(Password, PasswordLen, PasswordHash);
  ChallengeResponse(Challenge, PasswordHash, Response);
}