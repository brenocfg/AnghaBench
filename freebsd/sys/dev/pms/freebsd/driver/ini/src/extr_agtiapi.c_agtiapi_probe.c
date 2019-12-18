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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ag_card_info_t ;

/* Variables and functions */
 int AGTIAPI_MAX_CARDS ; 
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/ * agCardInfoList ; 
 int agtiapi_ProbeCard (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int agtiapi_probe( device_t dev )
{
  int retVal;
  int thisCard;
  ag_card_info_t *thisCardInst;

  thisCard = device_get_unit( dev );
  if ( thisCard >= AGTIAPI_MAX_CARDS ) 
  {
    device_printf( dev, "Too many PMC-Sierra cards detected ERROR!\n" );
    return (ENXIO); // maybe change to different return value?
  }
  thisCardInst = &agCardInfoList[ thisCard ];
  retVal = agtiapi_ProbeCard( dev, thisCardInst, thisCard );
  if ( retVal )
    return (ENXIO); // maybe change to different return value?
  return( BUS_PROBE_DEFAULT );  // successful probe
}