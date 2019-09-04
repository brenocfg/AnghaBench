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
typedef  int /*<<< orphan*/  md5_context ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md5_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  md5_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md5_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int md5_file( char *path, unsigned char output[16] )
{
    FILE *f;
    size_t n;
    md5_context ctx;
    unsigned char buf[1024];

    if( ( f = fopen( path, "rb" ) ) == NULL )
        return( 1 );

    md5_starts( &ctx );

    while( ( n = fread( buf, 1, sizeof( buf ), f ) ) > 0 )
        md5_update( &ctx, buf, (int) n );

    md5_finish( &ctx, output );

    memset( &ctx, 0, sizeof( md5_context ) );

    if( ferror( f ) != 0 )
    {
        fclose( f );
        return( 2 );
    }

    fclose( f );
    return( 0 );
}