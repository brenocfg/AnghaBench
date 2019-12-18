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
struct TYPE_3__ {char* key; char* value; struct TYPE_3__* next; } ;
typedef  TYPE_1__ epair_t ;
struct TYPE_4__ {TYPE_1__* epairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int Q3_MAX_MAP_ENTSTRING ; 
 TYPE_2__* entities ; 
 int num_entities ; 
 char* q3_dentdata ; 
 int q3_entdatasize ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void Q3_UnparseEntities (void)
{
	char *buf, *end;
	epair_t *ep;
	char line[2048];
	int i;
	
	buf = q3_dentdata;
	end = buf;
	*end = 0;
	
	for (i=0 ; i<num_entities ; i++)
	{
		ep = entities[i].epairs;
		if (!ep)
			continue;	// ent got removed
		
		strcat (end,"{\n");
		end += 2;
				
		for (ep = entities[i].epairs ; ep ; ep=ep->next)
		{
			sprintf (line, "\"%s\" \"%s\"\n", ep->key, ep->value);
			strcat (end, line);
			end += strlen(line);
		}
		strcat (end,"}\n");
		end += 2;

		if (end > buf + Q3_MAX_MAP_ENTSTRING)
			Error ("Entity text too long");
	}
	q3_entdatasize = end - buf + 1;
}