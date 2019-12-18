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
typedef  int u_char ;
typedef  int /*<<< orphan*/  MD5_CTX ;
typedef  int /*<<< orphan*/  MD4_CTX ;

/* Variables and functions */
 int AUTHLEN ; 
 size_t CHAP81_AUTHRESPONSE_LEN ; 
 size_t CHAP81_CHALLENGE_LEN ; 
 int CHAP81_HASH_LEN ; 
 int CHAP81_NTRESPONSE_OFF ; 
 int CHAP81_RESPONSE_LEN ; 
 int /*<<< orphan*/  GenerateAuthenticatorResponse (char*,size_t,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  GenerateNTResponse (char*,char*,char*,char*,size_t,char*) ; 
 int /*<<< orphan*/  GetMasterKey (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HashNtPasswordHash (char*,char*) ; 
 int /*<<< orphan*/  MD4Final (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Update (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  MD5Final (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  MPPE_MasterKey ; 
 int MS_CHAP_RESPONSE_LEN ; 
 int /*<<< orphan*/  NtPasswordHash (char*,size_t,char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  mschap_LANMan (char*,char*,char*) ; 
 int /*<<< orphan*/  mschap_NT (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *
chap_BuildAnswer(char *name, char *key, u_char id, char *challenge
#ifndef NODES
		 , u_char type, char *peerchallenge, char *authresponse,
		 int lanman
#endif
                )
{
  char *result, *digest;
  size_t nlen, klen;

  nlen = strlen(name);
  klen = strlen(key);

#ifndef NODES
  if (type == 0x80) {
    char expkey[AUTHLEN << 2];
    MD4_CTX MD4context;
    size_t f;

    if ((result = malloc(1 + nlen + MS_CHAP_RESPONSE_LEN)) == NULL)
      return result;

    digest = result;					/* the response */
    *digest++ = MS_CHAP_RESPONSE_LEN;			/* 49 */
    memcpy(digest + MS_CHAP_RESPONSE_LEN, name, nlen);
    if (lanman) {
      memset(digest + 24, '\0', 25);
      mschap_LANMan(digest, challenge + 1, key);	/* LANMan response */
    } else {
      memset(digest, '\0', 25);
      digest += 24;

      for (f = 0; f < klen; f++) {
        expkey[2*f] = key[f];
        expkey[2*f+1] = '\0';
      }
      /*
       *           -----------
       * expkey = | k\0e\0y\0 |
       *           -----------
       */
      MD4Init(&MD4context);
      MD4Update(&MD4context, expkey, klen << 1);
      MD4Final(digest, &MD4context);

      /*
       *           ---- -------- ---------------- ------- ------
       * result = | 49 | LANMan | 16 byte digest | 9 * ? | name |
       *           ---- -------- ---------------- ------- ------
       */
      mschap_NT(digest, challenge + 1);
    }
    /*
     *           ---- -------- ------------- ----- ------
     *          |    |  struct MS_ChapResponse24  |      |
     * result = | 49 | LANMan  |  NT digest | 0/1 | name |
     *           ---- -------- ------------- ----- ------
     * where only one of LANMan & NT digest are set.
     */
  } else if (type == 0x81) {
    char expkey[AUTHLEN << 2];
    char pwdhash[CHAP81_HASH_LEN];
    char pwdhashhash[CHAP81_HASH_LEN];
    char *ntresponse;
    size_t f;

    if ((result = malloc(1 + nlen + CHAP81_RESPONSE_LEN)) == NULL)
      return result;

    memset(result, 0, 1 + nlen + CHAP81_RESPONSE_LEN);

    digest = result;
    *digest++ = CHAP81_RESPONSE_LEN;		/* value size */

    /* Copy our challenge */
    memcpy(digest, peerchallenge + 1, CHAP81_CHALLENGE_LEN);

    /* Expand password to Unicode XXX */
    for (f = 0; f < klen; f++) {
      expkey[2*f] = key[f];
      expkey[2*f+1] = '\0';
    }

    ntresponse = digest + CHAP81_NTRESPONSE_OFF;

    /* Get some needed hashes */
    NtPasswordHash(expkey, klen * 2, pwdhash);
    HashNtPasswordHash(pwdhash, pwdhashhash);

    /* Generate NTRESPONSE to respond on challenge call */
    GenerateNTResponse(challenge + 1, peerchallenge + 1, name,
                       expkey, klen * 2, ntresponse);

    /* Generate MPPE MASTERKEY */
    GetMasterKey(pwdhashhash, ntresponse, MPPE_MasterKey);    /* XXX Global ! */

    /* Generate AUTHRESPONSE to verify on auth success */
    GenerateAuthenticatorResponse(expkey, klen * 2, ntresponse,
                                  peerchallenge + 1, challenge + 1, name,
                                  authresponse);

    authresponse[CHAP81_AUTHRESPONSE_LEN] = 0;

    memcpy(digest + CHAP81_RESPONSE_LEN, name, nlen);
  } else
#endif
  if ((result = malloc(nlen + 17)) != NULL) {
    /* Normal MD5 stuff */
    MD5_CTX MD5context;

    digest = result;
    *digest++ = 16;				/* value size */

    MD5Init(&MD5context);
    MD5Update(&MD5context, &id, 1);
    MD5Update(&MD5context, key, klen);
    MD5Update(&MD5context, challenge + 1, *challenge);
    MD5Final(digest, &MD5context);

    memcpy(digest + 16, name, nlen);
    /*
     *           ---- -------- ------
     * result = | 16 | digest | name |
     *           ---- -------- ------
     */
  }

  return result;
}