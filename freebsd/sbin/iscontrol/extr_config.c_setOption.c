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
typedef  int /*<<< orphan*/  isc_opt_t ;

/* Variables and functions */
 int /*<<< orphan*/  _CASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _OPT_BOOL (void*) ; 
 int /*<<< orphan*/  _OPT_INT (void*) ; 
 int /*<<< orphan*/  _OPT_STR (void*) ; 
 int /*<<< orphan*/  authMethod ; 
 int /*<<< orphan*/  chapDigest ; 
 int /*<<< orphan*/  chapIName ; 
 int /*<<< orphan*/  chapSecret ; 
 int /*<<< orphan*/  dataDigest ; 
 int /*<<< orphan*/  dataPDUInOrder ; 
 int /*<<< orphan*/  dataSequenceInOrder ; 
 int /*<<< orphan*/  defaultTime2Retain ; 
 int /*<<< orphan*/  defaultTime2Wait ; 
 int /*<<< orphan*/  errorRecoveryLevel ; 
 int /*<<< orphan*/  firstBurstLength ; 
 int /*<<< orphan*/  headerDigest ; 
 int /*<<< orphan*/  immediateData ; 
 int /*<<< orphan*/  initialR2T ; 
 int /*<<< orphan*/  initiatorAlias ; 
 int /*<<< orphan*/  initiatorName ; 
 int /*<<< orphan*/  iqn ; 
 int /*<<< orphan*/  maxBurstLength ; 
 int /*<<< orphan*/  maxConnections ; 
 int /*<<< orphan*/  maxOutstandingR2T ; 
 int /*<<< orphan*/  maxRecvDataSegmentLength ; 
 int /*<<< orphan*/  maxXmitDataSegmentLength ; 
 int /*<<< orphan*/  maxluns ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  sockbufsize ; 
 int /*<<< orphan*/  tags ; 
 int /*<<< orphan*/  targetAddress ; 
 int /*<<< orphan*/  targetAlias ; 
 int /*<<< orphan*/  targetName ; 
 int /*<<< orphan*/  targetPortalGroupTag ; 
 int /*<<< orphan*/  tgtChapName ; 
 int /*<<< orphan*/  tgtChapSecret ; 

__attribute__((used)) static void
setOption(isc_opt_t *op, int which, void *rval)
{
     switch(which) {
	  _CASE(port, _OPT_INT(rval));
	  _CASE(tags, _OPT_INT(rval));
	  _CASE(maxluns, _OPT_INT(rval));
	  _CASE(iqn, _OPT_STR(rval));
	  _CASE(sockbufsize, _OPT_INT(rval));

	  _CASE(maxConnections, _OPT_INT(rval));
	  _CASE(maxRecvDataSegmentLength, _OPT_INT(rval));
	  _CASE(maxXmitDataSegmentLength, _OPT_INT(rval));
	  _CASE(maxBurstLength, _OPT_INT(rval));
	  _CASE(firstBurstLength, _OPT_INT(rval));
	  _CASE(defaultTime2Wait, _OPT_INT(rval));
	  _CASE(defaultTime2Retain, _OPT_INT(rval));
	  _CASE(maxOutstandingR2T, _OPT_INT(rval));
	  _CASE(errorRecoveryLevel, _OPT_INT(rval));
	  _CASE(targetPortalGroupTag, _OPT_INT(rval));
	  _CASE(headerDigest, _OPT_STR(rval));
	  _CASE(dataDigest, _OPT_STR(rval));

	  _CASE(targetAddress, _OPT_STR(rval));
	  _CASE(targetAlias, _OPT_STR(rval));
	  _CASE(targetName, _OPT_STR(rval));
	  _CASE(initiatorName, _OPT_STR(rval));
	  _CASE(initiatorAlias, _OPT_STR(rval));
	  _CASE(authMethod, _OPT_STR(rval));
	  _CASE(chapSecret, _OPT_STR(rval));
	  _CASE(chapIName, _OPT_STR(rval));
	  _CASE(chapDigest, _OPT_STR(rval));

	  _CASE(tgtChapName, _OPT_STR(rval));
	  _CASE(tgtChapSecret, _OPT_STR(rval));

	  _CASE(initialR2T, _OPT_BOOL(rval));
	  _CASE(immediateData, _OPT_BOOL(rval));
	  _CASE(dataPDUInOrder, _OPT_BOOL(rval));
	  _CASE(dataSequenceInOrder, _OPT_BOOL(rval));
     }
}