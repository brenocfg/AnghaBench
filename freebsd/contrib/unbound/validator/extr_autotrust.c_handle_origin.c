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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/ * sldns_str2wire_dname (char*,size_t*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
handle_origin(char* line, uint8_t** origin, size_t* origin_len)
{
	size_t len = 0;
	while(isspace((unsigned char)*line))
		line++;
	if(strncmp(line, "$ORIGIN", 7) != 0)
		return 0;
	free(*origin);
	line += 7;
	while(isspace((unsigned char)*line))
		line++;
	*origin = sldns_str2wire_dname(line, &len);
	*origin_len = len;
	if(!*origin)
		log_warn("malloc failure or parse error in $ORIGIN");
	return 1;
}