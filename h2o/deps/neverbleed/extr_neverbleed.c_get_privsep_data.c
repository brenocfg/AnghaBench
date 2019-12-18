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
struct st_neverbleed_thread_data_t {int dummy; } ;
struct st_neverbleed_rsa_exdata_t {int /*<<< orphan*/  nb; } ;
typedef  int /*<<< orphan*/  RSA ;

/* Variables and functions */
 struct st_neverbleed_rsa_exdata_t* RSA_get_ex_data (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dief (char*) ; 
 scalar_t__ errno ; 
 struct st_neverbleed_thread_data_t* get_thread_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_privsep_data(const RSA *rsa, struct st_neverbleed_rsa_exdata_t **exdata,
                             struct st_neverbleed_thread_data_t **thdata)
{
    *exdata = RSA_get_ex_data(rsa, 0);
    if (*exdata == NULL) {
        errno = 0;
        dief("invalid internal ref");
    }
    *thdata = get_thread_data((*exdata)->nb);
}