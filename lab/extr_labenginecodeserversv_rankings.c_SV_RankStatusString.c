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
typedef  int GR_STATUS ;

/* Variables and functions */
#define  GR_STATUS_BADDOMAIN 140 
#define  GR_STATUS_BADGAME 139 
#define  GR_STATUS_BADPARAMS 138 
#define  GR_STATUS_BADPASSWORD 137 
#define  GR_STATUS_DOMAINLOCK 136 
#define  GR_STATUS_ERROR 135 
#define  GR_STATUS_INVALIDCONTEXT 134 
#define  GR_STATUS_INVALIDUSER 133 
#define  GR_STATUS_NETWORK 132 
#define  GR_STATUS_NOUSER 131 
#define  GR_STATUS_OK 130 
#define  GR_STATUS_PENDING 129 
#define  GR_STATUS_TIMEOUT 128 

__attribute__((used)) static char* SV_RankStatusString( GR_STATUS status )
{
	switch( status )
	{
		case GR_STATUS_OK:				return "GR_STATUS_OK";
		case GR_STATUS_ERROR:			return "GR_STATUS_ERROR";
		case GR_STATUS_BADPARAMS:		return "GR_STATUS_BADPARAMS";
		case GR_STATUS_NETWORK:			return "GR_STATUS_NETWORK";
		case GR_STATUS_NOUSER:			return "GR_STATUS_NOUSER";
		case GR_STATUS_BADPASSWORD:		return "GR_STATUS_BADPASSWORD";
		case GR_STATUS_BADGAME:			return "GR_STATUS_BADGAME";
		case GR_STATUS_PENDING:			return "GR_STATUS_PENDING";
		case GR_STATUS_BADDOMAIN:		return "GR_STATUS_BADDOMAIN";
		case GR_STATUS_DOMAINLOCK:		return "GR_STATUS_DOMAINLOCK";
		case GR_STATUS_TIMEOUT:			return "GR_STATUS_TIMEOUT";
		case GR_STATUS_INVALIDUSER:	    return "GR_STATUS_INVALIDUSER";
		case GR_STATUS_INVALIDCONTEXT:	return "GR_STATUS_INVALIDCONTEXT";
		default:						return "(UNKNOWN)";
	}
}