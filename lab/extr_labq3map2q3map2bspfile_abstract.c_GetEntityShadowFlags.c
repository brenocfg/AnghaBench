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
typedef  int /*<<< orphan*/  entity_t ;

/* Variables and functions */
 char* ValueForKey (int /*<<< orphan*/  const*,char*) ; 
 int atoi (char const*) ; 

void GetEntityShadowFlags( const entity_t *ent, const entity_t *ent2, int *castShadows, int *recvShadows ){
	const char  *value;


	/* get cast shadows */
	if ( castShadows != NULL ) {
		value = ValueForKey( ent, "_castShadows" );
		if ( value[ 0 ] == '\0' ) {
			value = ValueForKey( ent, "_cs" );
		}
		if ( value[ 0 ] == '\0' ) {
			value = ValueForKey( ent2, "_castShadows" );
		}
		if ( value[ 0 ] == '\0' ) {
			value = ValueForKey( ent2, "_cs" );
		}
		if ( value[ 0 ] != '\0' ) {
			*castShadows = atoi( value );
		}
	}

	/* receive */
	if ( recvShadows != NULL ) {
		value = ValueForKey( ent, "_receiveShadows" );
		if ( value[ 0 ] == '\0' ) {
			value = ValueForKey( ent, "_rs" );
		}
		if ( value[ 0 ] == '\0' ) {
			value = ValueForKey( ent2, "_receiveShadows" );
		}
		if ( value[ 0 ] == '\0' ) {
			value = ValueForKey( ent2, "_rs" );
		}
		if ( value[ 0 ] != '\0' ) {
			*recvShadows = atoi( value );
		}
	}
}