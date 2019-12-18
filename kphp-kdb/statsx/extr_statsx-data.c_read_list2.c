int* read_list2 () {
  int x = readin_int ();
  int y = readin_int ();
  assert (x >= y);
  int *a = zzmalloc0 (2 * (x + 1) * sizeof (int));
  assert (a);
  a[0] = x; a[1] = y; a += 2;
  readin ((char *)a, 2 * y * sizeof (int));
  return a;
}