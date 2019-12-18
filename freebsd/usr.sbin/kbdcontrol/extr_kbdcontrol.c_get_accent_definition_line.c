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
struct TYPE_5__ {TYPE_1__* acc; } ;
typedef  TYPE_2__ accentmap_t ;
struct TYPE_4__ {scalar_t__ accchar; int** map; } ;

/* Variables and functions */
 scalar_t__ ACC (void*) ; 
 scalar_t__ F_ACC ; 
 scalar_t__ L_ACC ; 
 int NUM_ACCENTCHARS ; 
#define  TLET 129 
#define  TNUM 128 
 int /*<<< orphan*/  errx (int,char*) ; 
 void* letter ; 
 void* number ; 
 char token ; 
 int /*<<< orphan*/  warnx (char*) ; 
 char yylex () ; 

__attribute__((used)) static int
get_accent_definition_line(accentmap_t *map)
{
	int accent;
	int c1, c2;
	int i;

	if (ACC(number) < F_ACC || ACC(number) > L_ACC)
		/* number out of range */
		return -1;
	accent = number;
	if (map->acc[accent].accchar != 0) {
		/* this entry has already been defined before! */
		errx(1, "duplicated accent key definition");
	}

	switch ((token = yylex())) {
	case TLET:
		map->acc[accent].accchar = letter;
		break;
	case TNUM:
		map->acc[accent].accchar = number;
		break;
	default:
		return -1;
	}

	for (i = 0; (token = yylex()) == '(';) {
		switch ((token = yylex())) {
		case TLET:
			c1 = letter;
			break;
		case TNUM:
			c1 = number;
			break;
		default:
			return -1;
		}
		switch ((token = yylex())) {
		case TLET:
			c2 = letter;
			break;
		case TNUM:
			c2 = number;
			break;
		default:
			return -1;
		}
		if ((token = yylex()) != ')')
			return -1;
		if (i >= NUM_ACCENTCHARS) {
			warnx("too many accented characters, ignored");
			continue;
		}
		map->acc[accent].map[i][0] = c1;
		map->acc[accent].map[i][1] = c2;
		++i;
	}
	return (accent + 1);
}