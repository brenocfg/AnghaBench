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
typedef  int /*<<< orphan*/  i ;
typedef  int /*<<< orphan*/  buf ;
typedef  char DesData ;
typedef  int /*<<< orphan*/  DES_key_schedule ;

/* Variables and functions */
 int /*<<< orphan*/  DES_DECRYPT ; 
 int /*<<< orphan*/  DES_cbc_encrypt (char*,char*,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DES_key_sched (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 

void
pk_decode(char *in, char *out, DesData *key)
{
	char buf[256];
	DesData i;
	DES_key_schedule k;
	int n1,n2,op;
	size_t l;

	memset(&i,0,sizeof(i));
	memset(buf,0,sizeof(buf));
	for (l=0,op=0;l<strlen(in)/2;l++,op+=2) {
		if (in[op] > '9')
			n1 = in[op] - 'A' + 10;
		else
			n1 = in[op] - '0';
		if (in[op+1] > '9')
			n2 = in[op+1] - 'A' + 10;
		else
			n2 = in[op+1] - '0';
		buf[l] = n1*16 +n2;
	}
	DES_key_sched(key, &k);
	DES_cbc_encrypt(buf, out, strlen(in) / 2, &k, &i, DES_DECRYPT);
	out[strlen(in)/2] = '\0';
}