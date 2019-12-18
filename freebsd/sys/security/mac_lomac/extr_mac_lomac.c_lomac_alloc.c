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
struct mac_lomac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_LOMAC ; 
 int M_ZERO ; 
 struct mac_lomac* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct mac_lomac *
lomac_alloc(int flag)
{
	struct mac_lomac *ml;

	ml = malloc(sizeof(*ml), M_LOMAC, M_ZERO | flag);

	return (ml);
}