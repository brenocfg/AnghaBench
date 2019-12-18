int print_snapshot_name (const char *name) {
  int l = strlen (name);
  assert (l >= 4 && !strcmp (name + l - 4, ".tmp") && l <= 256);
  return printf ("%.*s\n", l - 4, name);
}