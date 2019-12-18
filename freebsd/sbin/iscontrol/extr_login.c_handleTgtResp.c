#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdu_t ;
struct TYPE_4__ {TYPE_2__* op; } ;
typedef  TYPE_1__ isess_t ;
struct TYPE_5__ {char* tgtChapDigest; scalar_t__ initiatorName; scalar_t__ tgtChapName; } ;
typedef  TYPE_2__ isc_opt_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int,char*,int,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getkeyval (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int str2bin (char*,char**) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 

__attribute__((used)) static int
handleTgtResp(isess_t *sess, pdu_t *pp)
{
     isc_opt_t	*op = sess->op;
     char	*np, *rp, *d1, *d2;
     int	res, l1, l2;
     
     res = -1;
     if(((np = getkeyval("CHAP_N=", pp)) == NULL) ||
	((rp = getkeyval("CHAP_R=", pp)) == NULL))
	  goto out;
     if(strcmp(np, op->tgtChapName? op->tgtChapName: op->initiatorName) != 0) {
	  fprintf(stderr, "%s does not match\n", np);
	  goto out;
     }
     l1 = str2bin(op->tgtChapDigest, &d1);
     l2 = str2bin(rp, &d2);

     debug(3, "l1=%d '%s' l2=%d '%s'", l1, op->tgtChapDigest, l2, rp);
     if(l1 == l2 && memcmp(d1, d2, l1) == 0)
	res = 0;
     if(l1)
	  free(d1);
     if(l2)
	  free(d2);
 out:
     free(op->tgtChapDigest);
     op->tgtChapDigest = NULL;

     debug(3, "res=%d", res);

     return res;
}