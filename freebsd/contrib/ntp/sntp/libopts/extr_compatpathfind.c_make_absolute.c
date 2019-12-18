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

/* Variables and functions */
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *
make_absolute( char const * string, char const * dot_path )
{
    char * result;
    int result_len;

    if (!dot_path || *string == '/') {
        result = strdup( string );
	if (result == NULL) {
	return NULL;    /* couldn't allocate memory    */
	}
    } else {
        if (dot_path && dot_path[0]) {
            result = malloc( 2 + strlen( dot_path ) + strlen( string ) );
		if (result == NULL) {
		return NULL;    /* couldn't allocate memory    */
		}		
            strcpy( result, dot_path );
            result_len = (int)strlen(result);
            if (result[result_len - 1] != '/') {
                result[result_len++] = '/';
                result[result_len] = '\0';
            }
        } else {
            result = malloc( 3 + strlen( string ) );
		if (result == NULL) {
		return NULL;    /* couldn't allocate memory    */
		}
            result[0] = '.'; result[1] = '/'; result[2] = '\0';
            result_len = 2;
        }

        strcpy( result + result_len, string );
    }

    return result;
}