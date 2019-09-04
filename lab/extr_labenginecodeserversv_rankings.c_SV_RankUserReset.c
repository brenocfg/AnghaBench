#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int grank_status; } ;
struct TYPE_3__ {int value; } ;

/* Variables and functions */
#define  QGR_STATUS_BAD_PASSWORD 134 
#define  QGR_STATUS_ERROR 133 
 int QGR_STATUS_NEW ; 
#define  QGR_STATUS_NO_MEMBERSHIP 132 
#define  QGR_STATUS_NO_USER 131 
#define  QGR_STATUS_SPECTATOR 130 
#define  QGR_STATUS_TIMEOUT 129 
#define  QGR_STATUS_USER_EXISTS 128 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* s_ranked_players ; 
 int /*<<< orphan*/  s_rankings_active ; 
 TYPE_1__* sv_maxclients ; 

void SV_RankUserReset( int index )
{
	if( !s_rankings_active )
	{
		return;
	}

	assert( s_ranked_players != NULL );
	assert( index >= 0 );
	assert( index < sv_maxclients->value );

	switch( s_ranked_players[index].grank_status )
	{
	case QGR_STATUS_SPECTATOR:
	case QGR_STATUS_NO_USER:
	case QGR_STATUS_BAD_PASSWORD:
	case QGR_STATUS_USER_EXISTS:
	case QGR_STATUS_NO_MEMBERSHIP:
	case QGR_STATUS_TIMEOUT:
	case QGR_STATUS_ERROR:
		s_ranked_players[index].grank_status = QGR_STATUS_NEW;
		break;
	default:
		break;
	}
}