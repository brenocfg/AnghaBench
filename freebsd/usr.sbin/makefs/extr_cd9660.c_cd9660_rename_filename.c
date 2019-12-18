#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ verbose_level; int isoLevel; } ;
typedef  TYPE_2__ iso9660_disk ;
struct TYPE_11__ {char* o_name; TYPE_1__* isoDirRecord; } ;
typedef  TYPE_3__ cd9660node ;
struct TYPE_9__ {char* name; } ;

/* Variables and functions */
 int ISO_FILENAME_MAXLENGTH_BEFORE_VERSION ; 
 int /*<<< orphan*/  ISO_FILENAME_MAXLENGTH_WITH_PADDING ; 
 TYPE_3__* TAILQ_NEXT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cn_next_child ; 
 int dot ; 
 char* emalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static cd9660node *
cd9660_rename_filename(iso9660_disk *diskStructure, cd9660node *iter, int num,
    int delete_chars)
{
	int i = 0;
	int numbts, digit, digits, temp, powers, count;
	char *naming;
	int maxlength;
        char *tmp;

	if (diskStructure->verbose_level > 0)
		printf("Rename_filename called\n");

	assert(1 <= diskStructure->isoLevel && diskStructure->isoLevel <= 2);
	/* TODO : A LOT of chanes regarding 8.3 filenames */
	if (diskStructure->isoLevel == 1)
		maxlength = 8;
	else if (diskStructure->isoLevel == 2)
		maxlength = 31;
	else
		maxlength = ISO_FILENAME_MAXLENGTH_BEFORE_VERSION;

	tmp = emalloc(ISO_FILENAME_MAXLENGTH_WITH_PADDING);

	while (i < num && iter) {
		powers = 1;
		count = 0;
		digits = 1;
		while (((int)(i / powers) ) >= 10) {
			digits++;
			powers = powers * 10;
		}

		naming = iter->o_name;

		/*
		while ((*naming != '.') && (*naming != ';')) {
			naming++;
			count++;
		}
		*/

		while (count < maxlength) {
			if (*naming == ';')
				break;
			naming++;
			count++;
		}

		if ((count + digits) < maxlength)
			numbts = count;
		else
			numbts = maxlength - (digits);
		numbts -= delete_chars;

		/* 8.3 rules - keep the extension, add before the dot */

		/*
		 * This code makes a bunch of assumptions.
		 * See if you can spot them all :)
		 */

#if 0
		if (diskStructure->isoLevel == 1) {
			numbts = 8 - digits - delete_chars;
			if (dot < 0) {

			} else {
				if (dot < 8) {
					memmove(&tmp[numbts],&tmp[dot],4);
				}
			}
		}
#endif

		/* (copying just the filename before the '.' */
		memcpy(tmp, (iter->o_name), numbts);

		/* adding the appropriate number following the name */
		temp = i;
		while (digits > 0) {
			digit = (int)(temp / powers);
			temp = temp - digit * powers;
			sprintf(&tmp[numbts] , "%d", digit);
			digits--;
			numbts++;
			powers = powers / 10;
		}

		while ((*naming != ';')  && (numbts < maxlength)) {
			tmp[numbts] = (*naming);
			naming++;
			numbts++;
		}

		tmp[numbts] = ';';
		tmp[numbts+1] = '1';
		tmp[numbts+2] = '\0';

		/*
		 * now tmp has exactly the identifier
		 * we want so we'll copy it back to record
		 */
		memcpy((iter->isoDirRecord->name), tmp, numbts + 3);

		iter = TAILQ_NEXT(iter, cn_next_child);
		i++;
	}

	free(tmp);
	return iter;
}