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
typedef  scalar_t__ uc_err ;

/* Variables and functions */
 scalar_t__ UC_ERR_OK ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 char* uc_strerror (scalar_t__) ; 

void uc_trycall(uc_err res, const char *msg) {
    if (res != UC_ERR_OK) {
        printf("%s: %s\r\n", msg, uc_strerror(res));
        exit(1);
    }
}