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
typedef  int /*<<< orphan*/  Type ;
typedef  int /*<<< orphan*/ * List ;

/* Variables and functions */
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/ * append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  func (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltov (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  voidtype ; 

Type ftype(Type rty, Type ty) {
	List list = append(ty, NULL);

	list = append(voidtype, list);
	return func(rty, ltov(&list, PERM), 0);
}