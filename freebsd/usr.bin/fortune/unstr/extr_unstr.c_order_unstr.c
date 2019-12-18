#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  pos ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {scalar_t__ str_numstr; } ;
typedef  TYPE_1__ STRFILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  Dataf ; 
 int Delimch ; 
 int /*<<< orphan*/  Inf ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ STR_ENDSTRING (char*,TYPE_1__) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
order_unstr(STRFILE *tbl)
{
	uint32_t i;
	char *sp;
	off_t pos;
	char buf[BUFSIZ];

	for (i = 0; i < tbl->str_numstr; i++) {
		fread(&pos, 1, sizeof(pos), Dataf);
		fseeko(Inf, be64toh(pos), SEEK_SET);
		if (i != 0)
			printf("%c\n", Delimch);
		for (;;) {
			sp = fgets(buf, sizeof(buf), Inf);
			if (sp == NULL || STR_ENDSTRING(sp, *tbl))
				break;
			else
				fputs(sp, stdout);
		}
	}
}