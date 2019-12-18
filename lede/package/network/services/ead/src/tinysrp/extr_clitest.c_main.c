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
typedef  int /*<<< orphan*/  username ;
struct t_preconf {int /*<<< orphan*/  generator; int /*<<< orphan*/  modulus; } ;
struct t_num {char* data; void* len; } ;
struct t_client {int dummy; } ;
typedef  int /*<<< orphan*/  hexbuf ;

/* Variables and functions */
 int MAXHEXPARAMLEN ; 
 int MAXPARAMLEN ; 
 int MAXSALTLEN ; 
 int MAXUSERLEN ; 
 int RESPONSE_LEN ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  t_clientclose (struct t_client*) ; 
 struct t_num* t_clientgenexp (struct t_client*) ; 
 unsigned char* t_clientgetkey (struct t_client*,struct t_num*) ; 
 struct t_client* t_clientopen (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct t_num*) ; 
 int /*<<< orphan*/  t_clientpasswd (struct t_client*,char*) ; 
 unsigned char* t_clientresponse (struct t_client*) ; 
 scalar_t__ t_clientverify (struct t_client*,unsigned char*) ; 
 void* t_fromb64 (char*,char*) ; 
 int /*<<< orphan*/  t_fromhex (unsigned char*,char*) ; 
 int /*<<< orphan*/  t_getpass (char*,int,char*) ; 
 struct t_preconf* t_getpreparam (int) ; 
 char* t_tob64 (char*,char*,void*) ; 
 char* t_tohex (char*,unsigned char*,int) ; 

int
main()
{
  int index;
  struct t_client * tc;
  struct t_preconf *tcp;
  struct t_num s;
  struct t_num B;
  char username[MAXUSERLEN];
  char hexbuf[MAXHEXPARAMLEN];
  char buf1[MAXPARAMLEN], buf2[MAXPARAMLEN], buf3[MAXSALTLEN];
  unsigned char cbuf[20];
  struct t_num * A;
  unsigned char * skey;
  char pass[128];

  printf("Enter username: ");
  fgets(username, sizeof(username), stdin);
  username[strlen(username) - 1] = '\0';
  printf("Enter index (from server): ");
  fgets(hexbuf, sizeof(hexbuf), stdin);
  index = atoi(hexbuf);
  tcp = t_getpreparam(index - 1);
  printf("Enter salt (from server): ");
  fgets(hexbuf, sizeof(hexbuf), stdin);
  s.data = buf3;
  s.len = t_fromb64(s.data, hexbuf);

  tc = t_clientopen(username, &tcp->modulus, &tcp->generator, &s);
  if (tc == 0) {
    printf("invalid n, g\n");
    exit(1);
  }

  A = t_clientgenexp(tc);
  printf("A (to server): %s\n", t_tob64(hexbuf, A->data, A->len));

  t_getpass(pass, 128, "Enter password:");
  t_clientpasswd(tc, pass);

  printf("Enter B (from server): ");
  fgets(hexbuf, sizeof(hexbuf), stdin);
  B.data = buf1;
  B.len = t_fromb64(B.data, hexbuf);

  skey = t_clientgetkey(tc, &B);
  printf("Session key: %s\n", t_tohex(hexbuf, skey, 40));
  printf("Response (to server): %s\n",
    t_tohex(hexbuf, t_clientresponse(tc), RESPONSE_LEN));

  printf("Enter server response: ");
  fgets(hexbuf, sizeof(hexbuf), stdin);
  hexbuf[strlen(hexbuf) - 1] = '\0';
  t_fromhex(cbuf, hexbuf);

  if (t_clientverify(tc, cbuf) == 0)
    printf("Server authentication successful.\n");
  else
    printf("Server authentication failed.\n");

  t_clientclose(tc);

  return 0;
}