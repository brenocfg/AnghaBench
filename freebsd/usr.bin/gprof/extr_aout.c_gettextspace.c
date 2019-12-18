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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {scalar_t__ a_text; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  N_TXTOFF (TYPE_1__) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/ * textspace ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 TYPE_1__ xbuf ; 

__attribute__((used)) static void
gettextspace(FILE *nfile)
{

    textspace = (u_char *) malloc( xbuf.a_text );
    if ( textspace == NULL ) {
	warnx("no room for %u bytes of text space: can't do -c" ,
		  xbuf.a_text );
	return;
    }
    (void) fseek( nfile , N_TXTOFF( xbuf ) , 0 );
    if ( fread( textspace , 1 , xbuf.a_text , nfile ) != xbuf.a_text ) {
	warnx("couldn't read text space: can't do -c");
	free( textspace );
	textspace = 0;
	return;
    }
}