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
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  uLong ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int UNZ_OK ; 
 int /*<<< orphan*/  __LittleLong (int) ; 
 int /*<<< orphan*/  fread (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fread_ql (int*,int,int,int /*<<< orphan*/ *) ; 
 int unz_GAME_QL ; 

__attribute__((used)) static int unzlocal_getLong (FILE *fin, uLong *pX)
{
	int		v;

	if (unz_GAME_QL == 1) {
		fread_ql( &v, sizeof(v), 1, fin );
	} else {
		fread( &v, sizeof(v), 1, fin );
	}

	*pX = __LittleLong( v);
	return UNZ_OK;

/*
    uLong x ;
    int i;
    int err;

    err = unzlocal_getByte(fin,&i);
    x = (uLong)i;
    
    if (err==UNZ_OK)
        err = unzlocal_getByte(fin,&i);
    x += ((uLong)i)<<8;

    if (err==UNZ_OK)
        err = unzlocal_getByte(fin,&i);
    x += ((uLong)i)<<16;

    if (err==UNZ_OK)
        err = unzlocal_getByte(fin,&i);
    x += ((uLong)i)<<24;
   
    if (err==UNZ_OK)
        *pX = x;
    else
        *pX = 0;
    return err;
*/
}