#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
typedef  int /*<<< orphan*/  gentity_t ;
struct TYPE_3__ {int type; int /*<<< orphan*/  ofs; scalar_t__ name; } ;
typedef  TYPE_1__ field_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
#define  F_ANGLEHACK 132 
#define  F_FLOAT 131 
#define  F_INT 130 
#define  F_STRING 129 
#define  F_VECTOR 128 
 char* G_NewString (char const*) ; 
 int /*<<< orphan*/  Q_stricmp (scalar_t__,char const*) ; 
 float atof (char const*) ; 
 int atoi (char const*) ; 
 TYPE_1__* fields ; 
 int /*<<< orphan*/  sscanf (char const*,char*,float*,float*,float*) ; 

void G_ParseField( const char *key, const char *value, gentity_t *ent ) {
	field_t	*f;
	byte	*b;
	float	v;
	vec3_t	vec;

	for ( f=fields ; f->name ; f++ ) {
		if ( !Q_stricmp(f->name, key) ) {
			// found it
			b = (byte *)ent;

			switch( f->type ) {
			case F_STRING:
				*(char **)(b+f->ofs) = G_NewString (value);
				break;
			case F_VECTOR:
				sscanf (value, "%f %f %f", &vec[0], &vec[1], &vec[2]);
				((float *)(b+f->ofs))[0] = vec[0];
				((float *)(b+f->ofs))[1] = vec[1];
				((float *)(b+f->ofs))[2] = vec[2];
				break;
			case F_INT:
				*(int *)(b+f->ofs) = atoi(value);
				break;
			case F_FLOAT:
				*(float *)(b+f->ofs) = atof(value);
				break;
			case F_ANGLEHACK:
				v = atof(value);
				((float *)(b+f->ofs))[0] = 0;
				((float *)(b+f->ofs))[1] = v;
				((float *)(b+f->ofs))[2] = 0;
				break;
			}
			return;
		}
	}
}