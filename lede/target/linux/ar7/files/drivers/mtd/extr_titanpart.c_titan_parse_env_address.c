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
 int /*<<< orphan*/  printk (char*,char*,...) ; 
 char* prom_getenv (char*) ; 
 scalar_t__ simple_strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int	titan_parse_env_address(char *env_name, unsigned int *flash_base,
				unsigned int *flash_end)
{
	char	image_name[30];
	char	*env_ptr;
	char	*base_ptr;
	char	*end_ptr;
	char * string_ptr;
	/* Get the image variable */
	env_ptr = prom_getenv(env_name);
	if(!env_ptr){
		printk("titan: invalid env name, %s.\n", env_name);
		return -1;	/* Error, no image variable */
	}
	strncpy(image_name, env_ptr, 30);
	image_name[29]=0;
	string_ptr = image_name;
	/* Extract the start and stop addresses of the partition */
	base_ptr = strsep(&string_ptr, ",");
	end_ptr = strsep(&string_ptr, ",");
	if ((base_ptr == NULL) || (end_ptr == NULL)) {	
		printk("titan: Couldn't tokenize %s start,end.\n", image_name);
		return -1;
	}

	*flash_base = (unsigned int) simple_strtol(base_ptr, NULL, 0);
	*flash_end = (unsigned int) simple_strtol(end_ptr, NULL, 0);
	if((!*flash_base) || (!*flash_end)) {
		printk("titan: Unable to convert :%s: :%s: into start,end values.\n",
				env_name, image_name);
		return -1;
	}
	*flash_base &= 0x0fffffff;
	*flash_end &= 0x0fffffff;
	return 0;
}