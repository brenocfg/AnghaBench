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
typedef  int /*<<< orphan*/  tmap_info_t ;
typedef  int /*<<< orphan*/  const tOptionValue ;
typedef  int /*<<< orphan*/  tOptionLoadMode ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  OPTION_LOAD_COOKED ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ TEXT_MMAP_FAILED_ADDR (char*) ; 
 int errno ; 
 int /*<<< orphan*/  const* optionLoadNested (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_load_mode ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* text_mmap (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_munmap (int /*<<< orphan*/ *) ; 

const tOptionValue *
configFileLoad(char const * fname)
{
    tmap_info_t    cfgfile;
    tOptionValue * res = NULL;
    tOptionLoadMode save_mode = option_load_mode;

    char * txt = text_mmap(fname, PROT_READ, MAP_PRIVATE, &cfgfile);

    if (TEXT_MMAP_FAILED_ADDR(txt))
        return NULL; /* errno is set */

    option_load_mode = OPTION_LOAD_COOKED;
    res = optionLoadNested(txt, fname, strlen(fname));

    if (res == NULL) {
        int err = errno;
        text_munmap(&cfgfile);
        errno = err;
    } else
        text_munmap(&cfgfile);

    option_load_mode = save_mode;
    return res;
}