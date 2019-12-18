#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ pdu_t ;
struct TYPE_11__ {TYPE_3__* op; } ;
typedef  TYPE_2__ isess_t ;
struct TYPE_12__ {char* targetAddress; void* maxOutstandingR2T; void* dataDigest; void* headerDigest; void* targetPortalGroupTag; void* maxXmitDataSegmentLength; void* port; } ;
typedef  TYPE_3__ isc_opt_t ;
struct TYPE_14__ {char* name; int len; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* func ) (TYPE_2__*,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DigestMethods ; 
 int /*<<< orphan*/  GET ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_8__* keyMap ; 
 TYPE_8__* kp ; 
 TYPE_7__* mp ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 void* selectFrom (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 void* strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 void* strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int vflag ; 

__attribute__((used)) static void
processParams(isess_t *sess, pdu_t *pp)
{
     isc_opt_t		*op = sess->op;
     int		len, klen, n;
     char		*eq, *ptr;

     debug_called(3);

     len = pp->ds_len;
     ptr = (char *)pp->ds_addr;
     while(len > 0) {
	  if(vflag > 1)
	       printf("got: len=%d %s\n", len, ptr);
	  klen = 0;
	  if((eq = strchr(ptr, '=')) != NULL)
	       klen = eq - ptr;
	  if(klen > 0) {
	       if(strncmp(ptr, "TargetAddress", klen) == 0) {
		    char	*p, *q, *ta = NULL;

		    // TargetAddress=domainname[:port][,portal-group-tag]
		    // XXX: if(op->targetAddress) free(op->targetAddress);
		    q = op->targetAddress = strdup(eq+1);
		    if(*q == '[') {
			 // bracketed IPv6
			 if((q = strchr(q, ']')) != NULL) {
			      *q++ = '\0';
			      ta = op->targetAddress;
			      op->targetAddress = strdup(ta+1);
			 } else
			      q = op->targetAddress;
		    }
		    if((p = strchr(q, ',')) != NULL) {
			 *p++ = 0;
			 op->targetPortalGroupTag = atoi(p);
		    }
		    if((p = strchr(q, ':')) != NULL) {
			 *p++ = 0;
			 op->port = atoi(p);
		    }
		    if(ta)
			 free(ta);
	       } else if(strncmp(ptr, "MaxRecvDataSegmentLength", klen) == 0) {
		    // danny's RFC
		    op->maxXmitDataSegmentLength = strtol(eq+1, (char **)NULL, 0);
	       } else  if(strncmp(ptr, "TargetPortalGroupTag", klen) == 0) {
		    op->targetPortalGroupTag = strtol(eq+1, (char **)NULL, 0);
	       } else if(strncmp(ptr, "HeaderDigest", klen) == 0) {
		    op->headerDigest = selectFrom(eq+1, DigestMethods);
	       } else if(strncmp(ptr, "DataDigest", klen) == 0) {
		    op->dataDigest = selectFrom(eq+1, DigestMethods);
	       } else if(strncmp(ptr, "MaxOutstandingR2T", klen) == 0)
		    op->maxOutstandingR2T = strtol(eq+1, (char **)NULL, 0);
#if 0
	       else
	       for(kp = keyMap; kp->name; kp++) {
		    if(strncmp(ptr, kp->name, kp->len) == 0 && ptr[kp->len] == '=')
			 mp->func(sess, ptr+kp->len+1, GET);
	       }
#endif
	  }
	  n = strlen(ptr) + 1;
	  len -= n;
	  ptr += n;
     }

}